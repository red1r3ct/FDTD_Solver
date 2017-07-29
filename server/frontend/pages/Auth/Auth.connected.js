import {connect} from 'react-redux';
import Auth from './Auth';

const mapStateToProps = (state, ownProps) => ({});
const mapDispatchToProps = (dispatch, ownProps) => ({
	onLogin: () => {
		console.log("login");
	}
});

export default connect(mapStateToProps, mapDispatchToProps)(Auth);
