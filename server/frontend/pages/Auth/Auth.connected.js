import {connect} from 'react-redux';
import Auth from './Auth';
import {login} from '../../actions/auth';

const mapStateToProps = (state, ownProps) => ({});
const mapDispatchToProps = (dispatch, ownProps) => ({
	onLogin: (method) => {
		dispatch(login(method))
	}
});

export default connect(mapStateToProps, mapDispatchToProps)(Auth);
