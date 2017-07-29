import {connect} from 'react-redux';
import Loading from './Loading';

const mapStateToProps = (state, ownProps) => ({});
const mapDispatchToProps = (dispatch, ownProps) => ({
	checkAuth: () => {
		console.log("check auth");
	}
});

export default connect(mapStateToProps, mapDispatchToProps)(Loading);
